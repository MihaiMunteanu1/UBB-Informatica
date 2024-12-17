using NBA.domain;
using NBA.service;

namespace NBA.UI;

public class UI
{
    private Service service;
        public UI(Service service)
        { 
            this.service = service;
        }
        
        public void run()
        {
           while(true)
           {
                Console.WriteLine("\n");
                Console.WriteLine("0. Exit");
                Console.WriteLine("1. Afisearea tutror jucatorilor ai unei echipe date");
                Console.WriteLine("2. Afisarea tuturor jucatorilor activi ai unei echipe de la un anumit meci");
                Console.WriteLine("3. Afisarea tuturor meciurilor dintr-o anumita perioada calendaristica");
                Console.WriteLine("4. Afisarea scorului de la un anumit meci");
                Console.WriteLine("\n");

                Console.Write(">>>");
                try
                {
                    int cmd = int.Parse(Console.ReadLine());
                    Echipa e;
                    Meci m;
                    switch (cmd)
                    {
                        case 0:
                            return;
                        case 1:
                            Console.WriteLine("ID Echipa: ");
                            int idE = int.Parse(Console.ReadLine());
                            e = service.findEchipa(idE);
                            Console.WriteLine($"Jucatorii echipei {e.Name} sunt: ");
                            foreach (var jucator in service.JucatoriiUneiEchipe(e))
                                Console.WriteLine(jucator.Name + " , " + jucator.School);
                            break;
                        case 2:
                            Console.WriteLine("ID Echipa: ");
                            int idEchipa = int.Parse(Console.ReadLine());
                            e = service.findEchipa(idEchipa);
                            Console.WriteLine("ID Meci: ");
                            int idMeci = int.Parse(Console.ReadLine());
                            m = service.findMeci(idMeci);
                            Console.WriteLine($"Jucatorii activi ai echipei {e.Name} din meciul din {m.Date} sunt: ");
                            foreach (var jucator in service.JucatoriiActiviAiUneiEchipeDeLaMeciulX(e, m))
                            {
                                Console.WriteLine(jucator.Name + " , " + jucator.School);
                            }
                            break;
                        case 3:
                            Console.WriteLine("Din data de: ");
                            DateTime d1 = DateTime.Parse(Console.ReadLine());
                            Console.WriteLine("Pana in data de: ");
                            DateTime d2 = DateTime.Parse(Console.ReadLine());
                            foreach (var meci in service.MeciuriDinPerioadaX(d1, d2))
                            {
                                Console.WriteLine(meci.Team1.Name + " vs " + meci.Team2.Name + " din " + meci.Date);
                            }
                            break;
                        case 4:
                            Console.WriteLine("ID Meci: ");
                            int idM = int.Parse(Console.ReadLine());
                            m = service.findMeci(idM);
                            Console.WriteLine($"Scorul meciului dintre {m.Team1} si {m.Team2} din {m.Date} este: " + 
                                              service.ScorulUnuiMeci2(m));
                            break;
                    }
                }
                catch {
                    Console.WriteLine("Comanda invalida!");
                }
            }
        }
}