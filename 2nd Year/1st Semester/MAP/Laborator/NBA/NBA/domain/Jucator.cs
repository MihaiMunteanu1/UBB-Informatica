namespace NBA.domain;

public class Jucator : Elev
{
    private Echipa team { init; get; }
    

    public Echipa Team
    {
        get => team;
        init => team = value;
    }

    private bool Equals(Jucator other)
    {
        return team.Equals(other.team);
    }

    public override bool Equals(object? obj)
    {
        if (obj is null) return false;
        if (ReferenceEquals(this, obj)) return true;
        return obj.GetType() == GetType() && Equals((Jucator)obj);
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