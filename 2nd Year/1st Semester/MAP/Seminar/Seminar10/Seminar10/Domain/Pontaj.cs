using System.Runtime.InteropServices.ComTypes;

namespace Seminar10.Domain;

public class Pontaj
{
    private Angajat angajat { set; get; }
    private Sarcina sarcina { set; get; }
    private DateTime data;

    public Pontaj(DateTime data, Angajat angajat, Sarcina sarcina)
    {
        this.data = data;
        this.angajat = angajat;
        this.sarcina = sarcina;
    }

    public override string ToString()
    {
        return $"{nameof(data)}: {data}, {nameof(angajat)}: {angajat}, {nameof(sarcina)}: {sarcina}";
    }
}