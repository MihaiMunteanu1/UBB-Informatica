using System.Runtime.InteropServices.JavaScript;

namespace NBA.domain;

public class Meci : Entity<int>
{
    private Echipa team1 { set; get; }
    private Echipa team2 { set; get; }

    private DateTime data { set; get; }
    
    public Echipa Team1
    {
        get
        {
            return team1;
        }
        set
        {
            team1 = value;
        }
    }
    
    public Echipa Team2
    {
        get
        {
            return team2;
        }
        set
        {
            team2 = value;
        }
    }
    
    public DateTime Date
    {
        get
        {
            return data;
        }
        set
        {
            data = value;
        }
    }

    public override string ToString()
    {
        return $"{nameof(team1)}: {team1}, {nameof(team2)}: {team2}, {nameof(data)}: {data.ToString("dd/MM/yyyy")}";
    }
}