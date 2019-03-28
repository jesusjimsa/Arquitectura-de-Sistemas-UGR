#include <sys/mman.h>
#include <unistd.h>
#include <cassert>
#include <cstring>
#include <iostream>

int a, b;

int f1 () { return 2 * a - b + 3; }
int f1x() { return 2 * 2 - 3 + 3; } // when a=2 & b=3, f1() == f1x() == 4

int f2()
{
	int t = 0;
	for (int i = 0; i < 1000000 * a * b; ++i)
		t += 2 * a * a * a - b * b - 3;
	return t;
}

int f2x() // when a=2 & b=3, f2() == f2x() == 24000000
{
	return 24000000;
}

void fix_permissions(unsigned char *addr)
{
	std::size_t page_size = getpagesize();
	addr -= (std::size_t) addr % page_size;
	assert(mprotect(addr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) == 0);
}

struct __attribute__ ((__packed__)) payload
{
	unsigned char mov; // 1 byte
	int value;         // 4 bytes
	unsigned char ret; // 1 byte
};

template<class F> void test(F& f)
{
	int value = f();
	
	std::cout << "before: f() = " << f() << std::endl;
	
	// modifying f()
	fix_permissions((unsigned char*)f);
	payload p = {0xb8, value, 0xc3};
	memcpy((char*)f, (char*)&p, sizeof(p));
	
	std::cout << " after: f() = " << f() << std::endl;
	
	assert(value == f());
}

int main()
{
	std::cout << "a: ";
	std::cin >> a;
	std::cout << "b: ";
	std::cin >> b;
	std::cout << std::endl;
	
	test(f1);
	test(f2);
}

/*
0000000000401260 <f1()>:
  401260:	8b 05 5a 30 00 00    	mov    0x305a(%rip),%eax        # 4042c0 <a>
  401266:	01 c0                	add    %eax,%eax
  401268:	2b 05 4e 30 00 00    	sub    0x304e(%rip),%eax        # 4042bc <b>
  40126e:	83 c0 03             	add    $0x3,%eax
  401271:	c3                   	retq   
  401272:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000004012a8 <f1x()>:
  4012a8:	b8 04 00 00 00       	mov    $0x4,%eax
  4012ad:	c3                   	retq   

0000000000401278 <f2()>:
  401278:	8b 05 42 30 00 00    	mov    0x3042(%rip),%eax        # 4042c0 <a>
  40127e:	8b 35 38 30 00 00    	mov    0x3038(%rip),%esi        # 4042bc <b>
  401284:	89 c1                	mov    %eax,%ecx
  401286:	0f af ce             	imul   %esi,%ecx
  401289:	69 c9 40 42 0f 00    	imul   $0xf4240,%ecx,%ecx
  40128f:	85 c9                	test   %ecx,%ecx
  401291:	7e 1d                	jle    4012b0 <f2()+0x38>
  401293:	89 c2                	mov    %eax,%edx
  401295:	0f af f6             	imul   %esi,%esi
  401298:	0f af d0             	imul   %eax,%edx
  40129b:	0f af d0             	imul   %eax,%edx
  40129e:	01 d2                	add    %edx,%edx
  4012a0:	29 f2                	sub    %esi,%edx
  4012a2:	8d 42 fd             	lea    -0x3(%rdx),%eax
  4012a5:	0f af c1             	imul   %ecx,%eax
  4012a8:	c3                   	retq   
  4012a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  4012b0:	31 c0                	xor    %eax,%eax
  4012b2:	c3                   	retq   
  4012b3:	90                   	nop
  4012b4:	0f 1f 40 00          	nopl   0x0(%rax)

00000000004012d0 <f2x()>:
  4012d0:	b8 00 36 6e 01       	mov    $0x16e3600,%eax
  4012d5:	c3                   	retq   
  4012d6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
  4012dd:	00 00 00 
*/

