import cv2
import os
input=None
color=['Yellow','Orange','Blue','Red','Green','White']
'''function to find chromatacity of image'''
def chroma(img):
	#change img datatype
	img=img.astype('float32')
	#grama correction applied
	img=img**(22/10)
	#split color channels
	b,g,r=cv2.split(img)
	#calculate chromaticity
	Y=r+b+g
	R=r/Y
	G=g/Y
	B=b/Y
	#returning merged image
	return cv2.merge([B,G,R])

'''function to find colors in image using HSV'''
def getcolor(img):
	a=chroma(img)
	a=a*255
	a=a.astype('uint8')
	hsv = cv2.cvtColor(a, cv2.COLOR_BGR2HSV)
	avg=cv2.mean(hsv)
        print('average color -:',avg)
        global input
        for i in range(5):
	    input=readtxt(color[i],'getcolor.txt')
            cout=0
            for j in range(3):
                if(avg[j]<input[j+3] and avg[j]>input[j]):
                   cout=j
                   continue
                else:
                    break

            if(cout==2):
                return color[i]

def readtxt (name,filename):
    file = open(filename)
    a = file.readlines()
    d=[]
    for c in a:
	c = c.split(' ' or '/n')
	c=list(c)
	if c[0] == name :
	    for e in range(len(c)):
	        if(c[e].isdigit()):
		    d.append(int(c[e]))
            file.close()
            return d


x=639
y=479
i=6
config=str()
cap = cv2.VideoCapture(0)
while(i!=0):
    while(True):
        ret, img= cap.read()
        cv2.line(img,(x/2,0),(x/2,y),(255,0,0),1)
        cv2.line(img,(0,y/2),(x,y/2),(255,0,0),1)
        cv2.imshow('frame',img)
        k=cv2.waitKey(2)
        if k==27:
            break
    a=getcolor(img[0:x/2,0:y/2])
    b=getcolor(img[x/2:x,0:y/2])
    c=getcolor(img[0:x/2,y/2:y])
    d=getcolor(img[x/2:x,y/2:y])
    config=a+b+c+d
    print(config)
    i=i-1
cap.release()
cv2.destroyAllWindows()
