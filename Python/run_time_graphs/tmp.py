import re

text_example = """
fjdklasfjdsafd
safdsaf
dasf
dasf
dsa
fds
afd
saf
dsa
fds
a
"""

for mo in re.findall('af*', text_example, re.DOTALL | re.MULTILINE):
    print(mo)
