namespace NBA.domain;

public enum Tip{
    Activ, Rezerva
}

public class JucatorActiv : Entity<int>
{
    private int IdJucator { init; get; }
    private int IdMeci { init; get; }
    private int NrPuncteInscrise { get; init; }
    private Tip Tip { get; init; }


    public int IdPlayer
    {
        get => IdJucator;
        init => IdJucator = value;
    }
    
    public int IdGame
    {
        get => IdMeci;
        init => IdMeci = value;
    }
    
    public int NrPoints
    {
        get => NrPuncteInscrise;
        init => NrPuncteInscrise = value;
    }
    
    public Tip Type
    {
        get => Tip;
        init => Tip = value;
    }

    private bool Equals(JucatorActiv other)
    {
        return IdJucator == other.IdJucator && IdMeci == other.IdMeci && NrPuncteInscrise == other.NrPuncteInscrise && Tip == other.Tip;
    }

    public override bool Equals(object? obj)
    {
        if (obj is null) return false;
        if (ReferenceEquals(this, obj)) return true;
        return obj.GetType() == GetType() && Equals((JucatorActiv)obj);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(IdJucator, IdMeci, NrPuncteInscrise, (int)Tip);
    }

    public override string ToString()
    {
        return
            $"{nameof(IdJucator)}: {IdJucator}, {nameof(IdMeci)}: {IdMeci}, {nameof(NrPuncteInscrise)}: {NrPuncteInscrise}, {nameof(Tip)}: {Tip}";
    }
}