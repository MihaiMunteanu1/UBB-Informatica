using System.Runtime.InteropServices.JavaScript;

namespace NBA.domain;

public class Meci : Entity<int>
{
    private Echipa team1 { init; get; }
    private Echipa team2 { init; get; }

    private DateTime Data { init; get; }
    
    public Echipa Team1
    {
        get => team1;
        init => team1 = value;
    }
    
    public Echipa Team2
    {
        get => team2;
        init => team2 = value;
    }
    
    public DateTime Date
    {
        get => Data;
        init => Data = value;
    }

    public override string ToString()
    {
        return $"{nameof(team1)}: {team1}, {nameof(team2)}: {team2}, {nameof(Data)}: {Data:dd/MM/yyyy}";
    }
}