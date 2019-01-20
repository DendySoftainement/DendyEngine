#!/usr/bin/python

import os
import Tkinter
from Tkinter import *
import shutil


FileNameStr = ''

def ModuleDropdownChanged(newValue):
	CurrentModule = newValue
	SubMenuOptions = ModulesAndSubmodules[newValue]
	print SubMenuOptions
	SubVariable.set(ModulesAndSubmodules[newValue][0]) # default value
	DropDownSubModulesMenu["menu"].delete(0, "end")
	for SubMenuOptionName in SubMenuOptions:
		DropDownSubModulesMenu["menu"].add_command(label=SubMenuOptionName, command=lambda value=SubMenuOptionName: SubVariable.set(value))
		
		
		

def SubModuleDropdownChanged(newValue):
	CurrentSubModule = newValue



def CreateClass():
	print FileNameEntry.get()
	print ClassNameEntry.get()
	print Variable.get()
	print SubVariable.get()
	
	ModuleName = Variable.get()
	SubModuleName = SubVariable.get()
	FileName = FileNameEntry.get()
	ClassName = ClassNameEntry.get()
	
	
	HeaderTemplateFile = open('./Template.h', 'r')
	HeaderFile = open('./'+FileName+'.h', 'w')
	
	for Line in HeaderTemplateFile:
		NewLine = Line.replace("FILE", FileName)
		NewLine = NewLine.replace("MODULE", ModuleName)
		NewLine = NewLine.replace("SUB", SubModuleName)
		NewLine = NewLine.replace("CLASS", ClassName)
		HeaderFile.write( NewLine )
	
	HeaderTemplateFile.close()
	HeaderFile.close()
	
	BodyTemplateFile = open('./Template.cpp', 'r')
	BodyFile = open('./'+FileName+'.cpp', 'w')
	
	for Line in BodyTemplateFile:
		NewLine = Line.replace("FILE", FileName)
		NewLine = NewLine.replace("MODULE", ModuleName)
		NewLine = NewLine.replace("SUB", SubModuleName)
		NewLine = NewLine.replace("CLASS", ClassName)
		BodyFile.write( NewLine )
	
	BodyTemplateFile.close()
	BodyFile.close()
	
	
	
	# os.rename('./'+FileName+'.h', './code/'+ModuleName+'/'+SubModuleName+'/'+FileName+'.h')
	shutil.move('./'+FileName+'.h', './code/'+ModuleName+'/'+SubModuleName+'/'+FileName+'.h')
	
	# os.rename('./'+FileName+'.cpp', './code/'+ModuleName+'/'+SubModuleName+'/'+FileName+'.cpp')
	shutil.move('./'+FileName+'.cpp', './code/'+ModuleName+'/'+SubModuleName+'/'+FileName+'.cpp')
		
	
	
		
		
		
		
		
		
		
		
		
		
root = Tk()
root.title("Create new DEngine class")
root.minsize(400, 300)



ModulesAndSubmodules = {}

# for NotUsed, DirNamesVec, FileNamesVec in next(os.walk("./code"))[1]:
    # for DirName in DirNamesVec:
		# print DirName
	# for name in files:
        # if name.endswith((".html", ".htm")):

DirOrFileNamesVec = os.listdir("./code") # current directory
for DirOrFileName in DirOrFileNamesVec:
	if os.path.isdir("./code/"+DirOrFileName):
		ModulesAndSubmodules[DirOrFileName] = []
		SubDirOrFileNamesVec = os.listdir("./code/"+DirOrFileName)
		for SubDirOrFileName in SubDirOrFileNamesVec:
			if os.path.isdir("./code/"+DirOrFileName+"/"+SubDirOrFileName):
				ModulesAndSubmodules[DirOrFileName].append( SubDirOrFileName )
		

# for dir in dirList:
  # if os.path.isdir(dir) == True:
    # I don't know how to get into this dir and do the same thing here
  # else:
    # I got file and i can regexp if it is .htm|html

	

L1 = Label(root, text="File Name")
L1.pack( side = TOP)
FileNameEntry = Entry(root, bd =5)
FileNameEntry.pack(side = TOP)

L2 = Label(root, text="Class Name")
L2.pack( side = TOP)
ClassNameEntry = Entry(root, bd =5)
ClassNameEntry.pack(side = TOP)

LabelModules = Label(root, text="Module")
LabelModules.pack( side = TOP)
Variable = StringVar(root)
Variable.set(ModulesAndSubmodules.keys()[0]) # default value
DropDownModulesMenu = OptionMenu(root, Variable, *ModulesAndSubmodules.keys(), command=ModuleDropdownChanged)
DropDownModulesMenu.pack()



SubMenuOptions = ModulesAndSubmodules[ModulesAndSubmodules.keys()[0]]

LabelSubModules = Label(root, text="SubModule")
LabelSubModules.pack( side = TOP)
SubVariable = StringVar(root)
SubVariable.set(ModulesAndSubmodules[ModulesAndSubmodules.keys()[0]][0]) # default value
DropDownSubModulesMenu = OptionMenu(root, SubVariable, *SubMenuOptions, command=SubModuleDropdownChanged)
DropDownSubModulesMenu.pack()


CurrentModule = ModulesAndSubmodules.keys()[0]
CurrentSubModule = ModulesAndSubmodules[ModulesAndSubmodules.keys()[0]][0]

CreateButton = Button(root, text="Create class", command=CreateClass)
CreateButton.pack()


root.mainloop()

