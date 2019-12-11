print("Menu: \n\tEncrypt[1]\n\tDecrypt[2]\n\tExit[3]")
ans = None
while ans != "3":
  ascii = []
  ans = input("\nEnter your menu response: ")
  if ans == "1":
    text = list(input("\nEnter a message for encryption: "))
    for i in text:
      ascii.append(str(ord(i)) + ".")
    print("Encrypted: ")
    for i in range(0, len(ascii)):
      print(ascii[i], end="")
  elif ans == "2":
    text = (input("\nEnter a message for decryption: ")).split(".")
    for c in text:
      ascii.append(chr(int(c)))
    print("Decrypted:")
    for i in range(0, len(ascii)):
      print(ascii[i], end="")
