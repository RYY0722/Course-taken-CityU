/*
Question 1. Write a SQL to retrieve the TeamID and TeamName of teams that always 
got more points as home teams than away teams. [20 marks]
*/
	
CREATE VIEW HomePoints AS
SELECT TeamID, TName, G1.GameNo, SUM(Points)AS HTotal_points FROM Team AS T1,Game AS G1, Record AS R1
WHERE T1.TeamID = G1.HomeTeamID AND R1.GameNo = G1.GameNo AND 
PlayerID IN(SELECT PlayerID FROM Player WHERE Player.TeamID = T1.TeamID)
GROUP BY TeamID, TName, HomeTeamID, G1.GameNo;

CREATE VIEW AwayPoints AS
SELECT TeamID, TName, G1.GameNo, SUM(Points)AS ATotal_points FROM Team AS T1,Game AS G1, Record AS R1
WHERE T1.TeamID = G1.AwayTeamID AND R1.GameNo = G1.GameNo AND 
PlayerID IN(SELECT PlayerID FROM Player WHERE Player.TeamID = T1.TeamID)
GROUP BY TeamID, TName, AwayTeamID, G1.GameNo;

SELECT H.TeamID,H.TName
FROM AwayPoints AS A, HomePoints AS H
WHERE A.TeamID = H.TeamID
GROUP BY H.TeamID, H.TName
HAVING MIN(HTotal_points) >= MAX(ATotal_points);

--create view statement should be executed 1 by 1

/*
Question 2. Write a SQL to retrieve the PlayerID, PlayerName and Points of
 the players who achieve the highest point in a game. [20 marks]
*/
SELECT Player_1.PlayerID, Record_1.points, Player_1.PName 
FROM Player AS Player_1, Record AS Record_1
WHERE Record_1.PlayerID = Player_1.PlayerID AND
Record_1.Points  =
(
SELECT MAX(points) FROM Player AS Player_2, Record AS Record_2
WHERE Record_1.GameNo = Record_2.GameNo AND Record_2.PlayerID = Player_2.PlayerID
);
	

/*
Question 3. Write a SQL to retrieve the GameNo, TeamName, total points and total
 number of rebounds of a team (either home team or away team only) for each game
 and the team has the total number of rebounds per game larger than 30.
*/
SELECT G.GameNo,TName,SUM(R.Points)AS Total_Points,SUM(R.rebounds) AS Total_Rebounds
FROM Game AS G, Team AS T, Record AS R
WHERE (G.AwayTeamID = T.TeamID OR G.HomeTeamID = T.TeamID) AND R.GameNo = G.GameNo AND 
R.PlayerID IN (SELECT PlayerID FROM Player AS P WHERE P.TeamID = T.TeamID)
GROUP BY G.GameNo,TName
HAVING SUM(R.rebounds) >= 30