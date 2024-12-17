using ConsoleApp1;
using ConsoleApp1.Repository;
using ConsoleApp1.Service;

IRepository<Angajat, string> repositoryA = new AngajatFileRepository("data/angajati.txt");
IRepository<Sarcina, string> repositoryS = new SarcinaFileRepository("data/sarcini.txt");
IRepository<Pontaj, string> repositoryP = new PontajFileRepository("C:\\Users\\munte\\RiderProjects\\Sem10\\ConsoleApp1\\data\\pontaje.txt", repositoryA, repositoryS);

Service service = new Service(repositoryA, repositoryS, repositoryP);


//service.SortAngajatiByNivelAndVenit().ForEach(Console.WriteLine);

// foreach (var keyValuePair in service.GetAverageDurationPerDifficulty())
// {
//     Console.WriteLine(keyValuePair.Key + " " + keyValuePair.Value);
// }

//service.GetTop2HardWorkingEmployees().ForEach(Console.WriteLine);
