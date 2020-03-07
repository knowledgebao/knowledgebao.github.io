from ctypes import *

lib = CDLL("build/example.dll")

add_v9 = lib.add_v9
add_v9.argtypes = [c_int, c_int, POINTER(c_int)]
add_v9.restype = c_int

out = c_int()
print(add_v9(1,2,byref(out)))
print(out.value)

sprint = lib.sprint 
sprint.argtypes = [POINTER(c_char), c_char, c_int, c_char_p]
sprint.restype = c_int

buf = (c_char*255)()
count = sprint(cast(buf, c_char_p), ord('A'), 33, b"hello")
print(count)
print(buf[:])
print(buf[:count])