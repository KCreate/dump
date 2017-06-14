# C++ code

```c++
// Example program
#include <iostream>
#include <string>

using namespace std;

struct Foo {
    int virtual foo() { return 1; }
    int virtual bar() { return 1; }
};

struct Bar : public Foo {
    int virtual foo() { return 2; }
    int virtual bar() { return 2; }
};

int call(Foo* foo) {
    return foo->foo() + foo->bar();
}

int main() {
    Foo* foo = new Foo();
    Bar* bar = new Bar();

    int result;

    result = call(foo);
    result = call(bar);

    return 0;
} 
```

# Produced assembly (x86_64 gcc 7.1, unoptimized code)

```asm
std::ios_base::Init::Init()@plt-0x10:
  push   QWORD PTR [rip+0x200a02]        # 601008 <_GLOBAL_OFFSET_TABLE_+0x8>
  jmp    QWORD PTR [rip+0x200a04]        # 601010 <_GLOBAL_OFFSET_TABLE_+0x10>
  nop    DWORD PTR [rax+0x0]
std::ios_base::Init::Init()@plt:
  jmp    QWORD PTR [rip+0x200a02]        # 601018 <_GLOBAL_OFFSET_TABLE_+0x18>
  push   0x0
  jmp    400600 <_init+0x28>
std::ios_base::Init::~Init()@plt:
  jmp    QWORD PTR [rip+0x2009ea]        # 601030 <_GLOBAL_OFFSET_TABLE_+0x30>
  push   0x3
  jmp    400600 <_init+0x28>
operator new(unsigned long)@plt:
  jmp    QWORD PTR [rip+0x2009e2]        # 601038 <_GLOBAL_OFFSET_TABLE_+0x38>
  push   0x4
  jmp    400600 <_init+0x28>
.plt.got:
  jmp    QWORD PTR [rip+0x200992]        # 600ff8 <_DYNAMIC+0x200>
  xchg   ax,ax
main:
  push   rbp
  push   rbx
  mov    edi,0x8
  sub    rsp,0x8
  call   400650 <operator new(unsigned long)@plt>
  mov    edi,0x8
  mov    rbp,rax
  mov    QWORD PTR [rax],0x400920
  call   400650 <operator new(unsigned long)@plt>
  mov    rbx,rax
  mov    QWORD PTR [rax],0x400940
  mov    rax,QWORD PTR [rbp+0x0]
  mov    rdi,rbp
  call   QWORD PTR [rax]
  mov    rax,QWORD PTR [rbp+0x0]
  mov    rdi,rbp
  call   QWORD PTR [rax+0x8]
  mov    rax,QWORD PTR [rbx]
  mov    rdi,rbx
  call   QWORD PTR [rax]
  mov    rax,QWORD PTR [rbx]
  mov    rdi,rbx
  call   QWORD PTR [rax+0x8]
  add    rsp,0x8
  xor    eax,eax
  pop    rbx
  pop    rbp
  ret    
  nop    DWORD PTR [rax+rax*1+0x0]
call(Foo*):
  push   rbp
  push   rbx
  mov    rbx,rdi
  sub    rsp,0x8
  mov    rax,QWORD PTR [rdi]
  call   QWORD PTR [rax]
  mov    ebp,eax
  mov    rax,QWORD PTR [rbx]
  mov    rdi,rbx
  call   QWORD PTR [rax+0x8]
  add    rsp,0x8
  add    eax,ebp
  pop    rbx
  pop    rbp
  ret    
  nop    WORD PTR cs:[rax+rax*1+0x0]
  nop    DWORD PTR [rax+0x0]
Foo::foo():
  mov    eax,0x1
  ret    
  nop    WORD PTR cs:[rax+rax*1+0x0]
Foo::bar():
  mov    eax,0x1
  ret    
  nop    WORD PTR cs:[rax+rax*1+0x0]
Bar::foo():
  mov    eax,0x2
  ret    
  nop    WORD PTR cs:[rax+rax*1+0x0]
Bar::bar():
  mov    eax,0x2
  ret    
  nop    WORD PTR cs:[rax+rax*1+0x0]
```
