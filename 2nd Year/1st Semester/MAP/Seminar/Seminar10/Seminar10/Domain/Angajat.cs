using System.Runtime.InteropServices.ComTypes;

namespace Seminar10.Domain;

public class Angajat
{
    private string angajatId { set; get; }
    private string nume { set; get; }
    private float veneitPeOra { set; get; }
    private Enum nivel { set; get; }

    public Angajat(string angajatId, string nume, float veneitPeOra, Enum nivel)
    {
        this.angajatId = angajatId;
        this.nume = nume;
        this.veneitPeOra = veneitPeOra;
        this.nivel = nivel;
    }

    public override string ToString()
    {
        return
            $"{nameof(angajatId)}: {angajatId}, {nameof(nume)}: {nume}, {nameof(veneitPeOra)}: {veneitPeOra}, {nameof(nivel)}: {nivel}";
    }
}