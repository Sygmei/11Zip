# 11Zip
Dead simple zipping / unzipping C++ Lib

I didn't really wanted to make my own zipping / unzipping library but as I found nothing else, I made my own.

For now you have access to two functions which are really simple :

```
elz::extractZip(std::string zipName, std::string target = ".");
```

Which just unzip the content of a zip in "target" folder (which is current folder by default).

and the other function is : 

```
elz::zipFolder(std::string folderName, std::string zipTarget = "");
```

Which just zip the folder "folderName" to "zipTarget" (Which is "folderName".zip by default).
