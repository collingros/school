print("Menu: \n\tEncrypt[1]\n\tDecrypt[2]\n\tExit[3]")
ans = None
while ans != "3":
  ascii = []
  ans = input("\nEnter your menu response: ")
  if ans == "1":
    text = list(input("\nEnter a message for encryption: "))
    for i in text:
      ascii.append(ord(i))
    print("Encrypted: ")
    for i in range(0, len(ascii)):
      print(ascii[i], end="")
  elif ans == "2":
    text = list(input("\nEnter a message for decryption: "))
    i = 0
    while i < (len(text) - 1):
      if text[i] == "1":
        ascii.append(chr(int(text[i] + text[i+1] + text[i+2])))
        i += 3
      elif text[i] in ["2", "3", "4", "5", "6", "7", "8", "9", "10"]:
        ascii.append(chr(int(text[i] + text[i + 1])))
        i += 2
      else:
        i += 1
    print("Decrypted:")
    for i in range(0, len(ascii)):
      print(ascii[i], end="")
