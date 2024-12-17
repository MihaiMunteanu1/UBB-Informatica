namespace NBA.domain;

public class Jucator : Elev
{
    private Echipa team { set; get; }
    

    public Echipa Team
    {
        get
        {
            return team;
        }
        set
        {
            team = value;
        }
    }

    protected bool Equals(Jucator other)
    {
        return team.Equals(other.team);
    }

    public override bool Equals(object? obj)
    {
        if (obj is null) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != GetType()) return false;
        return Equals((Jucator)obj);
    }

    public override int GetHashCode()
    {
        return team.GetHashCode();
    }

    public override string ToString()
    {
        return $"{base.ToString()}, {nameof(Team)}: {Team}";
    }
}