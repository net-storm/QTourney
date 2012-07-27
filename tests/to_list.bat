cat 1.txt | sed 's/FirstName="\([^ ]*\)" MiddleName="\([^ ]*\)" LastName="\([^ ]*\)" Nickname="\([^ ]*\)" ShortNameType="\([^ ]*\)" .*/\4:team:score:tournaments:wins:ties:loses:\1:\2:\3:\5/g' > out.txt

