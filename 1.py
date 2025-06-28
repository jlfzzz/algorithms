from typing import Counter


def f(size:int, alignment:int)->int:

    return (size + alignment - 1) & ~(alignment - 1)

print(f(309939,8192))
print(f(309939, 8192) // 8192)

s1="123"
s1 = "0" * 2 + s1
print(s1)

arr1 = [31311, 121]
print(arr1)
arr2 = arr1
print(arr2)

arr2.append(3)
print(arr1)
print(arr2)
