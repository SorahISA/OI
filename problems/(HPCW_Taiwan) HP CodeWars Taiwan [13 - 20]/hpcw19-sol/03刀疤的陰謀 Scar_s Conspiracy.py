
def solution(number):
  primeList = []
  result = tryDivision(number, 2)
  if result != number:
    primeList.insert(0, 2)
    number = result

  divisor = 3
  while number >= divisor:
    result = tryDivision(number, divisor)
    if result != number:
      primeList.insert(0, divisor)
      number = result
    divisor += 2

  for prime in primeList:
    print prime


def tryDivision(dividend, divisor):
  if dividend == 0:
    return 0
  
  while True:
    quotient = dividend / divisor
    remainder = dividend % divisor
    if remainder == 0:
      dividend = quotient
    else:
      return dividend

if __name__ == '__main__':
  solution(int(raw_input()))

# if __name__ == '__main__':
#   while True:
#     try:
#       num = raw_input()
#       solution(int(num))
#       print '--'
#     except EOFError:
#       break
