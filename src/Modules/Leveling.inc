#include <YSI_Coding\y_hooks>

#define BASE_LEVELING_HOURS     2
@hook(.fallback = true) pTask1s(playerid)
{
    if((PlayerAccountInfo[playerid][TimePlayed] % 60) == 0) 
    {
        if((++PlayerCharInfo[playerid][TimeMinutes] % 60) == 0) 
        {
            PlayerCharInfo[playerid][TimeHours]++;
            new TargetPoint = PlayerCharInfo[playerid][Level] * BASE_LEVELING_HOURS;
            if(PlayerCharInfo[playerid][TimeHours] >= TargetPoint) 
            {
                PlayerCharInfo[playerid][Level]++;
                PlayerCharInfo[playerid][LevelPoint] = PlayerCharInfo[playerid][Level] * BASE_LEVELING_HOURS;
                SetPlayerScore(playerid, PlayerCharInfo[playerid][Level]);
                GameTextForPlayer(playerid, va_return("~b~~h~~h~~h~You just leveled up to ~y~~h~%d", PlayerCharInfo[playerid][Level]), 500, 1);

                new query[128];
                mysql_format(Database, query, sizeof query, "UPDATE `characters` SET `LevelPoint`=%d WHERE `ID`=%d", PlayerCharInfo[playerid][LevelPoint], PlayerCharInfo[playerid][ID]);
                mysql_tquery(Database, query);
            }
        }
    }
    return 1;
}