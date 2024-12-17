using System.Globalization;
using System.Runtime.CompilerServices;

namespace ConsoleApp1.Repository;

public class PontajFileRepository : FileRepository<Pontaj, string>
{
    private readonly IRepository<Angajat, string> _repoA;
    private readonly IRepository<Sarcina, string> _repoS;

    public PontajFileRepository(string filePath, IRepository<Angajat, string> repoA, IRepository<Sarcina, string> repoS)
        : base(filePath, line => StringToEntity(line, repoA, repoS), EntityToString)
    {
        _repoA = repoA ?? throw new ArgumentNullException(nameof(repoA));
        _repoS = repoS ?? throw new ArgumentNullException(nameof(repoS));
    }

    private static Pontaj StringToEntity(string line, IRepository<Angajat, string> repoA, IRepository<Sarcina, string> repoS)
    {
        string[] tokens = line.Split(',');
        string id = tokens[0] + "," + tokens[1];
        Angajat angajat = repoA.FindOne(tokens[0]);
        Sarcina sarcina = repoS.FindOne(tokens[1]);

        DateTime data = DateTime.ParseExact(tokens[2], "dd/MM/yyyy", CultureInfo.InvariantCulture);
        return new Pontaj { Id = id, Angajat = angajat, Sarcina = sarcina, Data = data };
    }

    private static string EntityToString(Pontaj pontaj)
    {
        return pontaj.Angajat + "," + pontaj.Sarcina + "," + pontaj.Data.ToString("dd/MM/yyyy");
    }
}