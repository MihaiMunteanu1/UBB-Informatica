namespace Seminar10.Domain;

public class Sarcina
{
    private string sarcinaId { set; get; }
    private Enum dificultate;
    private int nrOreEstimate { set; get; }

    public Sarcina(Enum dificultate, string sarcinaId, int nrOreEstimate)
    {
        this.dificultate = dificultate;
        this.sarcinaId = sarcinaId;
        this.nrOreEstimate = nrOreEstimate;
    }

    public override string ToString()
    {
        return
            $"{nameof(dificultate)}: {dificultate}, {nameof(sarcinaId)}: {sarcinaId}, {nameof(nrOreEstimate)}: {nrOreEstimate}";
    }
}