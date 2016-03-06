#!/usr/bin/env python

import configparser

def CreateConfigFile():
    config = configparser.ConfigParser()

    config["Default"] = {}
    config["Default"]["key"] = "Value"
    config["Default"]["key2"] = "value2"
    config["Default"]["key3"] = "value3"

    with open("example.ini", "w") as configfile:
        config.write(configfile)

# configStructrue = {
        # "SectionName" : {
            # "key1" : "value1",
            # "key2" : "value2"
            # }
        # }

def ReadConfigFile(filename):
    config = configparser.ConfigParser()
    config.read(filename)
    allConfig = {}
    for sectionName in config:
        section = config[sectionName]
        allConfig[sectionName] = {}
        for itemName in section:
            allConfig[sectionName][itemName] = config[sectionName][itemName]

    return allConfig

# def ReadConfigFile(filename, itemnames):
    # config = configparser.ConfigParser()
    # config.read(filename)
    # for sectionName in config:
        # section = config[sectionName]
        # for itemName in section:
            # if itemName in itemnames:
                # print(itemName + "=" + config[sectionName][itemName])

def GetSpecificConfig(filename, itemlist):
    config = ReadConfigFile(filename)
    for section in config:
        for item in config[section]:
            if item in itemlist:
                print("[%s]:[%s]:[%s]=[%s]" % (filename, section, item, config[section][item]))

items = {
        "example.ini" : ["key", "key2"],
        "tmp.ini" : ["key", "key3"]
        }

# CreateConfigFile()

for fileName in items:
    GetSpecificConfig(fileName, items[fileName])

