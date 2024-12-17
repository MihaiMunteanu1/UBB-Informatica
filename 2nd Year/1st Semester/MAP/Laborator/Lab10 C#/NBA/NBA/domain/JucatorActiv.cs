namespace NBA.domain;

public enum Tip{
    Activ, Rezerva
}

public class JucatorActiv : Entity<int>
{
    private int idJucator { set; get; }
    private int idMeci { set; get; }
    private int nrPuncteInscrise { set; get; }
    private Tip tip { set; get; }
    

    public int idPlayer
    {
        get
        {
            return idJucator;
        }
        set
        {
            idJucator = value;
        }
    }
    
    public int idGame
    {
        get
        {
            return idMeci;
        }
        set
        {
            idMeci = value;
        }
    }
    
    public int nrPoints
    {
        get
        {
            return nrPuncteInscrise;
        }
        set
        {
            nrPuncteInscrise = value;
        }
    }
    
    public Tip Type
    {
        get
        {
            return tip;
        }
        set
        {
            tip = value;
        }
    }

    protected bool Equals(JucatorActiv other)
    {
        return idJucator == other.idJucator && idMeci == other.idMeci && nrPuncteInscrise == other.nrPuncteInscrise && tip == other.tip;
    }

    public override bool Equals(object? obj)
    {
        if (obj is null) return false;
        if (ReferenceEquals(this, obj)) return true;
        if (obj.GetType() != GetType()) return false;
        return Equals((JucatorActiv)obj);
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(idJucator, idMeci, nrPuncteInscrise, (int)tip);
    }

    public override string ToString()
    {
        return
            $"{nameof(idJucator)}: {idJucator}, {nameof(idMeci)}: {idMeci}, {nameof(nrPuncteInscrise)}: {nrPuncteInscrise}, {nameof(tip)}: {tip}";
    }
}