// search.js

// Check whether given character exists in array
function exist(array, character) {
    for (var i = 0; i < array.length; i++) {
        if (array[i] == character) return true;
    }
    return false;
}

// Check whether given filter matches the string (e.g. "ce" would match "Cecilia")
// The check is case-insensitive
function checkFilter(filter, string) {
    if (filter.length > string.length) return false;

    var filterlower = filter.toLowerCase();
    var stringlower = string.toLowerCase();

    for (var i = 0; i < filter.length; i++) {
        if (filterlower[i] != stringlower[i])
            return false;
    }

    return true;
}

// Updates the filtermodel based on the current filter
function updateFilterModel(name)
{

}

// Updates the array of unique first letters in the current index of the model
function updateUniqueChars() {
    if (filtermodel == undefined) return;

    var characters = new Array();

    // If filter model has at most 1 item in it, no point in going
    // any further with filtering
    if (filtermodel.count > 1) {

        for (var i = 0; i < filtermodel.count; i++) {
            var name = filtermodel.get(i).name;
            if (!exist(characters, name[filter.length])) {
                characters.push(name[filter.length])
            }
        }

        characters.sort()
    }


    uniqueChars = characters
}

// Returns the text for a filter button in the given index
// Returned value is a single (unique) character or "<" (backspace)
function filterButtonText(index) {
    if (uniqueChars == undefined) return 0;
    if (index == uniqueChars.length) return "<";
    return uniqueChars[index].toUpperCase();
}

// Number of buttons in the filter panel
function filterButtonCount() {
    if (uniqueChars == undefined) return 0;
    if (filter.length == 0) return uniqueChars.length;
    return uniqueChars.length
}

function sortByTeam(a, b) 
{
     var x = a.team.toLowerCase();
     var y = b.team.toLowerCase();
     return ((x < y) ? -1 : ((x > y) ? 1 : 0));
}

// Fills the filtermodel with contents from the source list's model
function fillFilterModel() 
{
    if (fullModel == undefined) return;

    console.log("count: " + fullModel.count);

//	fullModel.move(107,1,1);

	for(var i = 0; i < fullModel.count; i++)  // i - номер прохода
	{            
	    for(var j = fullModel.count-1; j > i; j-- )  // внутренний цикл прохода
	    {     
	    	if ( fullModel.get(j-1).team < fullModel.get(j).team)
	      	{
	      		console.log("swapping " + (j-1) + " with " + j )
				fullModel.move(j-1,j,1)
	    	}
	    }
	}
}
