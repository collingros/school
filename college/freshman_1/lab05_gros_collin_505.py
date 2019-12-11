#Name: Collin Gros
#CS 1411
#10/10/2017
#Make a website using user-entered data in HTML.
#Given - 
'''<html>
<head>
<title>My web page</title>
</head>
<body>
<p>There are many pictures of my cat here,
as well as my <b>very cool</b> blog page,
which contains <font color="red">awesome</font>
stuff about my trip to the Grand Canyon.</p>
<p>Here is my cat now.
<img src="Day
-60-
Denby.jpg">
</body>
</html> '''

#Analysis: Need to make functions to write to a file
#Method / Algorithm
#functions
#introduction
#menu
#print file

#Test cases
#t - Hello should type a line "Hello"
#c - Hello - red make a line "Hello" red
#e - should exit
#i - should add image
#b - should bold


#Website Creation Program

#functions
def check_file_validity(file): #checks to see if filename exists
  try:
    htmlfile = open(file, 'r')
    print("That file already exists!")
    htmlfile.close()
    return False
  except FileNotFoundError:
    return True
def html_setup(file, web_title): #beginning of html file
  string1 = "<html>\n<head>\n<title>{}</title>\n</head>\n<body>\n<p>\n".format(web_title)
  file.write(string1)
def html_end(file):#end of html file
  file.write("</p>\n</body>\n</html>\n")
def text_line(file):#Adds a line of text 
  user_text_line = input("Please enter a line of text: ")
  new_user_text_line = "{}<br />\n".format(user_text_line)
  file.write(new_user_text_line)
def image(file):#Adds an image
  d = False
  while not d:
    user_image_string = input("Please enter the name of the image: ")
    try:
      testfile = open(user_image_string, 'r')
      testfile.close()
      d = True
    except FileNotFoundError:
      print("That file does not exist.")
      response = input("Press 'e' to exit the image menu(or press another key to try again): ")#gives user opportunity to exit image selection
      if response[0] == 'e':
        d = True
      else:
        d = False
  new_user_image_string = "<img src=\"{}\"><br />\n".format(user_image_string)
  file.write(new_user_image_string)
def bold_line(file):#Bolds and adds a line
  user_bold_line = input("Please enter a line of text to be bolded: ")
  new_user_bold_line = "<b> {} </b><br />\n".format(user_bold_line)
  file.write(new_user_bold_line)
def colored_line(file):#Colors and adds a line
  user_colored_line = input("Please enter a line of text to be colored: ")
  user_color_choice = input("Please enter a color for your line: ")
  new_user_colored_line = "<font color=\"{}\">{}</font><br />\n".format(user_color_choice, user_colored_line)
  file.write(new_user_colored_line)
#introduction
print("Welcome to the Website-Making Program!")
#creating the file
filename = input("Please enter a filename for the website(include .html): ")
done = False
while not done:#Validation
  if check_file_validity(filename):
    done = True
  else:
    filename = input("Please enter a filename for the website(include .html): ")
#opening webfile
webfile = open(filename, "a")
#creating the webpage title
webtitle = str(input("Enter a title for your webpage:"))
#current variables: webfile, webtitle
html_setup(webfile, webtitle)
gotvalue = False
while not gotvalue:
  print("Webpage Options:\n[t]ext line\n[i]mage\n[b]old line\n[c]olored line\n[e]xit")
  value = input("Please enter your choice: ")
  if value[0] == 't':
    text_line(webfile)
    print("Your changes have been saved...\n")
  elif value[0] == 'i':
    image(webfile)
    print("Your changes have been saved...\n")
  elif value[0] == 'b':
    bold_line(webfile)
    print("Your changes have been saved...\n")
  elif value[0] == 'c':
    colored_line(webfile)
    print("Your changes have been saved...\n")
  elif value[0] == 'e':
    print("Exiting...\n")
    gotvalue = True
  else:
    print("The choice you entered is not valid.")
#reading and printing the file
html_end(webfile)
webfile.close()
webfile2 = open(filename, 'r')
for line in webfile2:
  print(line)
finished = input("Press enter to continue...")
#create menu options, call functions for each option

#assign responses to strings
