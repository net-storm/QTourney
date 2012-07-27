.pragma library

function serialize_all(value) {
	return " : " + value.name
		 + " : " + value.team
		 + " : " + value.score
		 + " : " + value.tours
		 + " : " + value.wins
		 + " : " + value.ties
		 + " : " + value.loses
		 + " : " + value.first_name
		 + " : " + value.middle_name
		 + " : " + value.last_name
		 + " : " + value.hits
		 + " : " + value.forfeits
		 + " : " + value.the_rest
	;
}

function serialize(value) {
	return ": " + value.name
		+ " : " + value.team
		+ " :" //+ value.score
		+ ":" //+ value.tours
		+ ":" //+ value.wins
		+ ":" //+ value.ties
		+ ":" //+ value.loses
		+ ":" //+ value.first_name
		+ ":" //+ value.middle_name
		+ ":" //+ value.last_name
		+ ": "  + value.hits
		+ " : " + value.forfeits
		+ " :"//+ value.the_rest
	;
}
