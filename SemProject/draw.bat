@echo OFF
cd Drawer
call gswin64c.exe -q -dSAFER -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=%1.pdf %1
start %1.pdf