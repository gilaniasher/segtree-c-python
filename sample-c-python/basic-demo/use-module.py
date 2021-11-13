'''
Sample script verifying that we can use our C extension
as a Python module
'''

import spam
res = spam.demo('echo "my program is working!"')
print(f'Result: {res}')
