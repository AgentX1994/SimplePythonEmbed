'''Contains a multiplication subroutine'''

def multiply(first_number, second_number):
    '''Returns the result of multiplying first_number and second_number'''
    print("Will compute", first_number, "times", second_number)
    result = 0
    for _ in range(0, first_number):
        result = result + second_number
    return result
