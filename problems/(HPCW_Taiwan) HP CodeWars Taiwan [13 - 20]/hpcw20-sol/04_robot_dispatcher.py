'''
忍者村規定大家外出都必須戴口罩，身上沒口罩的，村長會想辦法送給你
但因為要減少人和人面對面的接觸，忍者村決議用自動機器人去送口罩，
自動機器人只能接收非負的整數數列，其中每個元素代表他最多能從這點前進的步數，
並且要能從最初的出發地，拜訪到最後的一個位置，請幫村長設計一個驗證數列的系統
'''

def jumpGame(nums: list):
    farthest = 0
    for i in range(len(nums)):
        if (farthest < i):
            return False
        farthest = max(farthest, i + nums[i])
    return True


if __name__ == "__main__":
    nums = input()
    nums = nums.replace("[", "")
    nums = nums.replace("]", "")
    nums = list(map(int, nums.split(",")))
    print(jumpGame(nums))
