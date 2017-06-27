from appJar import gui



app=gui("Grid Demo", "600x250")
control = gui("control", "300x300")
app.setSticky("news")
app.setExpand("both")
squareName = ""
width = 0
length = 0
pattern = []
patternList = []
h1 = []
h2 = []
h3 = []
h4 = []
p1 = []
p2 = []
p3 = []
p4 = []
p5 = []
p6 = []
pedal1 = []
pedal2 = []
pedal3 = []
pedal4 = []
pedal5 = []
pedal6 = []
pat = []

def addArrays(array1, array2):
    if len(array1) ==0:
        for x in range(0,len(array2)):
            array1.append(array2[x])
    for i in range(0,len(array1)):
        if array2[i] == "1":
            array1[i] = "1"
    return array1


def fillPattern():
    global width
    global length
    global pattern
    global patternList
    global h1
    global h2
    global h3
    global h4
    global p1
    global p2
    global p3
    global p4
    global p5
    global p6

    global pedal1
    global pedal2
    global pedal3
    global pedal4
    global pedal5
    global pedal6



    global pat
    warp = control.getEntry("warp").split()
    width = len(warp)
    pat = control.getEntry("pattern").split(";")
    patternList = []
    for i in range(0, len(pat)):
        patternList.append([])
        patternList[i] = pat[i].split()
    print2DArray(patternList)
    length = len(pat)
    for i in range(0,length):
        pattern.append([])
        for j in range(0,width):
            pattern[i].append("0")
    p1 = control.getEntry("p1").split()
    p2 = control.getEntry("p2").split()
    p3 = control.getEntry("p3").split()
    p4 = control.getEntry("p4").split()
    p5 = control.getEntry("p5").split()
    p6 = control.getEntry("p6").split()

    for i in range(0,len(warp)):
        if(warp[i] == "1"):
            h1.append("1")
            h2.append("0")
            h3.append("0")
            h4.append("0")

        if (warp[i] == "2"):
            h1.append("0")
            h2.append("1")
            h3.append("0")
            h4.append("0")

        if (warp[i] == "3"):
            h1.append("0")
            h2.append("0")
            h3.append("1")
            h4.append("0")

        if (warp[i] == "4"):
            h1.append("0")
            h2.append("0")
            h3.append("0")
            h4.append("1")


    print("h2:", h2)
    for i in range(0, len(p1)):
        if(p1[i]=="1"):
            pedal1 = addArrays(pedal1,h1)
        if (p1[i] == "2"):
            pedal1 =  addArrays(pedal1, h2)
        if (p1[i] == "3"):
            pedal1 = addArrays(pedal1, h3)
        if (p1[i] == "4"):
            pedal1 = addArrays(pedal1, h4)

    for i in range(0, len(p2)):
        if(p2[i]=="1"):
            pedal2 = addArrays(pedal2,h1)
        if (p2[i] == "2"):
            pedal2 = addArrays(pedal2, h2)
        if (p2[i] == "3"):
            pedal2 = addArrays(pedal2, h3)
        if (p2[i] == "4"):
            pedal2 = addArrays(pedal2, h4)

    for i in range(0, len(p3)):
        if(p3[i]=="1"):
            pedal3 = addArrays(pedal3,h1)
        if (p3[i] == "2"):
            pedal3 = addArrays(pedal3, h2)
        if (p3[i] == "3"):
            pedal3 = addArrays(pedal3, h3)
        if (p3[i] == "4"):
            pedal3 = addArrays(pedal3, h4)

    for i in range(0, len(p4)):
        if(p4[i]=="1"):
            pedal4 = addArrays(pedal4,h1)
        if (p4[i] == "2"):
            pedal4 = addArrays(pedal4, h2)
        if (p4[i] == "3"):
            pedal4 = addArrays(pedal4, h3)
        if (p4[i] == "4"):
            pedal4 = addArrays(pedal4, h4)

    for i in range(0, len(p5)):
        if(p5[i]=="1"):
            pedal5 = addArrays(pedal5,h1)
        if (p5[i] == "2"):
            pedal5 = addArrays(pedal5, h2)
        if (p5[i] == "3"):
            pedal5 = addArrays(pedal5, h3)
        if (p5[i] == "4"):
            pedal5 = addArrays(pedal5, h4)

    for i in range(0, len(p6)):
        if(p6[i]=="1"):
            pedal6 = addArrays(pedal6,h1)
        if (p6[i] == "2"):
            pedal6 = addArrays(pedal6, h2)
        if (p6[i] == "3"):
            pedal6 = addArrays(pedal6, h3)
        if (p6[i] == "4"):
            pedal6 = addArrays(pedal6, h4)


    i = length-1
    n = 0
    while(i>=0):
        for j in range(0, len(patternList[i])):
            if patternList[i][j] == "1":
                pattern[n] = addArrays(pattern[n],pedal1)
            if patternList[i][j] == "2":
                pattern[n] = addArrays(pattern[n], pedal2)
            if patternList[i][j] == "3":
                pattern[n] = addArrays(pattern[n], pedal3)
            if patternList[i][j] == "4":
                pattern[n] = addArrays(pattern[n], pedal4)
            if patternList[i][j] == "5":
                pattern[n] = addArrays(pattern[n], pedal5)
            if patternList[i][j] == "6":
                pattern[n] = addArrays(pattern[n], pedal6)


        i-=1
        n+=1


def print2DArray(array):
    print('   ', end='')

    print("")
    for i in range(len(array)):

        for j in range(len(array[i])):
            print(array[i][j], ' ', end='')
        print()

def press(btn):
    global width
    global length
    global pattern
    global patternList
    global h1
    global h2
    global h3
    global h4
    global p1
    global p2
    global p3
    global p4
    global p5
    global p6
    global pedal1
    global pedal2
    global pedal3
    global pedal4
    global pedal5
    global pedal6
    global pat

    w = 2
    l = 2
    if btn == "Start":
            fillPattern()
            print2DArray(pattern)



            #change width
            temp = []
            for x in range(0,len(pattern)):
                temp = pattern[x]
                for y in range(w):
                    for z in range(len(temp)):
                        pattern[x].append(temp[z])

            width = len(pattern[0])
            n = length
            #change length
            for i in range(l):
                for x in range(0, len(pattern)):
                    temp = pattern[x]
                    pattern.append([])
                    pattern[n] = temp
                    n+=1

            length = len(pattern)
            for i in range(0,length):
                for j in range(0,width):
                    squareName =  str(i) + 'x' + str(j)

                    app.addLabel(squareName, "", i, j)
                    if pattern[i][j] == "1":
                        app.setLabelBg(squareName, "White")
                    else:
                        app.setLabelBg(squareName, "Black")

            control.stop()

            app.go()
    if btn == "Default":
        control.setEntry("warp", "1 2 3 2 1 4 3 2 1 2 3 4")
        control.setEntry("p1", "")
        control.setEntry("p2", "")
        control.setEntry("p3", "1 2 3")
        control.setEntry("p4", "1 2 4")
        control.setEntry("p5", "1 3 4")
        control.setEntry("p6", "2 3 4")
        control.setEntry("pattern", "3;4;5;6;5;4;3;6;5;4;5;6")








control.addLabel("warpP", "Warp pattern: ", 1, 0)              # Row 1,Column 0
control.addEntry("warp", 1, 1,1)
control.addLabel("pedal1", "Pedal 1 hookup: ", 2, 0)  # Row 1,Column 0
control.addEntry("p1", 2, 1,1)
control.addLabel("pedal2", "Pedal 2 hookup: ", 3, 0)  # Row 1,Column 0
control.addEntry("p2", 3, 1,1)
control.addLabel("pedal3", "Pedal 3 hookup: ", 4, 0)  # Row 1,Column 0
control.addEntry("p3", 4, 1,1)
control.addLabel("pedal4", "Pedal 4 hookup: ", 5, 0)  # Row 1,Column 0
control.addEntry("p4", 5, 1,1)
control.addLabel("pedal5", "Pedal 5 hookup: ", 6, 0)  # Row 1,Column 0
control.addEntry("p5", 6, 1,1)
control.addLabel("pedal6", "Pedal 6 hookup: ", 7, 0)  # Row 1,Column 0
control.addEntry("p6", 7, 1,1)
control.addLabel("pat", "Pattern: ", 8, 0)  # Row 1,Column 0
control.addEntry("pattern", 8, 1,1)

# Row 1,Column 1

control.addButton("Start", press, 9,0,3)
control.addButton("Default", press, 10,0,3)

control.go()
