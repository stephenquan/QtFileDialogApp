# QtFileDialogApp

This app was created to explore the changes in Qt 5.13.0 and its support for the native FileDialog in Android.

In building this app, I observed the following on a Nexus 5P running Android 8.0.0:

 - The FileDialog.fileUrl URI is non human readable
   - 1. A user triggers the FileDialog
   - 2. User selects a recognizable file, from their Google Drive, say, "brownfox.txt"
   - 3. The FileDialog displays a cryptic URL, e.g. "content://com.google.android.apps.doc.storage/document/abc123abc123"
 - The fileUrl is no longer persistable
   - 1. A user selects a file using FileDialog
   - 2. App persists the fileUrl using QSettings
   - 3. User exits the app
   - 4. User loads the app
   - 5. User attempts to work with the fileUrl, but an exception occurs
 - QFile no longer fully works
   - QFile.exists always reports false on Android
   - QFile.fileName is always empty string "" on Android
   - QFile.size is always 0 on Android
   - However, the user can still read the file with QFile( url + "" ).readAll()
 - QFileInfo no longer full works
   - QFileInfo.absolutePath returns a cryptic /data/data folder on Android
   - QFileInfo.absoluteFilePath returns a cryptic /data/data/ filename on Android
   - QFileInfo.baseName is cryptic on Android
   - QFileInfo.exists on Android
   - QFileInfo.fileName is cryptic on Android
   - QFileInfo.filePath returns the cryptic fileUrl on Android
   - QFileInfo.size is always 0 on Android
   
 References:
  - https://bugreports.qt.io/browse/QTBUG-76886
