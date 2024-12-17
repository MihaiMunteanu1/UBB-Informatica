using ConsoleApp1.Repository;

namespace ConsoleApp1.Service;

public class Service
{
    private IRepository<Angajat,string> AngajatRepository;
    private IRepository<Sarcina,string> SarcinaRepository;
    private IRepository<Pontaj, string> PontajRepository;

    public Service(IRepository<Angajat, string> angajatFileRepository,  IRepository<Sarcina, string> sarcinaFileRepository,
        IRepository<Pontaj, string> pontajRepository)
    {
        AngajatRepository = angajatFileRepository;
        SarcinaRepository = sarcinaFileRepository;
        PontajRepository = pontajRepository;
    }

    public List<Angajat> findAngajati()
    {
        return AngajatRepository.FindAll().ToList();
    }
    
    public List<Sarcina> findSarcini()
    {
        return SarcinaRepository.FindAll().ToList();
    }
    
    public List<Pontaj> findPontaje()
    {
        return PontajRepository.FindAll().ToList();
    }

    public List<Angajat> SortAngajatiByNivelAndVenit()
    {
        return AngajatRepository.FindAll()
            .OrderBy(angajat => angajat.Nivel)
            .ThenBy(angajat => angajat.VenitPeOra)
            .ToList();
    }

    public Dictionary<Dificultate, double> GetAverageDurationPerDifficulty()
    {
        return SarcinaRepository.FindAll()
            .GroupBy(sarcina => sarcina.Dificultate)
            .ToDictionary(
                group => group.Key,
                group => group.Average(sarcina => sarcina.NrOreEstimate)
            );
    }
    
    public List<Angajat> GetTop2HardWorkingEmployees()
    {
        var pontaje = PontajRepository.FindAll();
        var angajati = AngajatRepository.FindAll();

        var earnings = pontaje
            .GroupBy(p => p.Angajat.Id)
            .Select(g => new
            {
                AngajatId = g.Key,
                TotalEarnings = g.Sum(p => p.Data.Hour * angajati.First(a => a.Id == g.Key).VenitPeOra)
            })
            .OrderByDescending(e => e.TotalEarnings)
            .Take(2)
            .Select(e => angajati.First(a => a.Id == e.AngajatId))
            .ToList();

        return earnings;
    }
}