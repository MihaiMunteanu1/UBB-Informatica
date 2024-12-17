using NBA;
using NBA.domain;
using NBA.repository;
using NBA.repository.file;
using NBA.service;
using NBA.UI;

public class Program
{
    public static void Main(String[] args)
    {
        IRepository<int,Echipa> echipaFileRepo = new EchipaFileRepo("C:\\Users\\munte\\RiderProjects\\NBA\\NBA\\data\\echipa.txt");

        IRepository<int, Elev> elevFileRepo = new ElevFileRepo("C:\\Users\\munte\\RiderProjects\\NBA\\NBA\\data\\elev.txt");
        
        IRepository<int, JucatorActiv> jucatorActivFileRepo = new JucatorActivFileRepo("C:\\Users\\munte\\RiderProjects\\NBA\\NBA\\data\\jucatoractiv.txt");
        
        IRepository<int, Jucator> jucatorFileRepo = new JucatorFileRepo("C:\\Users\\munte\\RiderProjects\\NBA\\NBA\\data\\jucator.txt",echipaFileRepo);
        
        IRepository<int, Meci> meciFileRepo = new MeciFileRepo("C:\\Users\\munte\\RiderProjects\\NBA\\NBA\\data\\meci.txt",echipaFileRepo);
        
        Service service = new Service(echipaFileRepo, elevFileRepo, jucatorFileRepo, meciFileRepo, jucatorActivFileRepo);

        UI ui = new UI(service);
        
        ui.run();
        
        Console.WriteLine(DateTime.Now);
    }
    
}
