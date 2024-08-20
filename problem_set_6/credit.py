import re


def main():
    card = input("Number: ")

    cardType = GetCardType(card)
    if cardType != "INVALID" and not ValidateCheckSum(card):
        cardType = "INVALID"
    print(cardType)


def ValidateCheckSum(card):
    # Validate whether the checksum of the card
    # aligns with the Luhn’s Algorithm

    sum, counter = 0, 0
    for i in range(len(card)-1, -1, -1):
        if counter % 2 == 0:
            sum += int(card[i])
        else:
            num = int(card[i]) * 2
            if num > 9:
                sum += 1 + (num % 10)
            else:
                sum += num
        counter += 1

    return (sum % 10) == 0


def GetCardType(card):
    # Get the card type based on the length and starting numbers

    # AMEX
    if re.match("3[4,7]", card) and len(card) == 15:
        return "AMEX"
    # MASTERCARD
    elif re.match("5[1-5]", card) and len(card) == 16:
        return "MASTERCARD"
    # VISA
    elif re.match("4", card) and (len(card) == 13 or len(card) == 16):
        return "VISA"
    else:
        return "INVALID"


main()
