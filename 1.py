def f(size:int, alignment:int)->int:

    return (size + alignment - 1) & ~(alignment - 1)

print(f(309939,8192))
print(f(309939, 8192) // 8192)

s1="123"
s1 = "0" * 2 + s1
print(s1)
