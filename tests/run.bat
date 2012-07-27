@Echo off

REM using pipes (cygwin):
cat list.txt | form_pairs -s random > pairs.txt 

REM using file:
form_pairs -s random -f list.txt > pairs.txt