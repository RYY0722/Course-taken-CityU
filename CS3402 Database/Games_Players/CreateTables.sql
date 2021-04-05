if OBJECT_ID('Player') is null
create table Player
(PlayerID int not null,
 PName char(10),
 Position char(15),
 TeamID int
 primary key(PlayerID)
 );

 if OBJECT_ID('Team') is null
 create table Team
 (
	TeamID int not null,
	TName char(15),
	Venue char(15)
	primary key(TeamID));

if OBJECT_ID('Game') is null
create table Game(
	GameNo int not null,
	GDate date,
	GTime decimal(7,2),
	HomeTeamID int,
	AwayTeamID int
	primary key(GameNo)
	);

if OBJECT_ID('Record') is null
create table Record(
	GameNo int not null default -1,
	PlayerID int not null,
	Points int,
	Rebounds int,
	Assists int,
	primary key(GameNo, PlayerID)
	);
	
/*	SELECT PlayerID, PName FROM Player EXCEPT (select Player.PlayerID, PName 
	from Player, Record where Player.PlayerID = Record.PlayerID)


	SELECT T.TeamID, TName, COUNT(PlayerID) FROM Player AS P, Team AS T WHERE
	T.TeamID = P.PlayerID GROUP BY T.TeamID, TName;

	SELECT P.PlayerID, PName FROM Player AS P, Record AS R, Game AS G WHERE
	P.PlayerID = R.PlayerID AND G.GameNo = R.GameNo GROUP BY P.PlayerID, PName 
	HAVING COUNT(PName) >=2;
	*/