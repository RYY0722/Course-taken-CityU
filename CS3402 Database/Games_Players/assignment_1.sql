/*
Question 4. Write a SQL to retrieve the TeamID, TeamName and the number of players for each 
team. [20 marks]
*/
	
	SELECT PlayerID, PName FROM Player EXCEPT (select Player.PlayerID, PName 
	from Player, Record where Player.PlayerID = Record.PlayerID)


/*
Question 5. Write a SQL to retrieve the PlayerID and PName of players who played for their team 
in two or more games. [20 marks]
*/
	SELECT P.PlayerID, PName FROM Player AS P, Record AS R, Game AS G WHERE
	P.PlayerID = R.PlayerID AND G.GameNo = R.GameNo GROUP BY P.PlayerID, PName 
	HAVING COUNT(PName) >=2;
	