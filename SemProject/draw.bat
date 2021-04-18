@echo OFF
cd Drawer
call gswin64.exe -q -dSAFER -dBATCH -dNOPAUSE -sDEVICE=pdfwrite -sOutputFile=%1.pdf %1
start %1.pdf