﻿using NBA.domain;
using NBA.service;

namespace NBA.UI;

public class Ui(Service service)
{
    public void Run()
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
                    var cmd = int.Parse(Console.ReadLine() ?? string.Empty);
                    Echipa e;
                    Meci m;
                    switch (cmd)
                    {
                        case 0:
                            return;
                        case 1:
                            Console.WriteLine("ID Echipa: ");
                            var idE = int.Parse(Console.ReadLine() ?? string.Empty);
                            e = service.FindEchipa(idE);
                            Console.WriteLine($"Jucatorii echipei {e.Name} sunt: ");
                            foreach (var jucator in service.JucatoriiUneiEchipe(e))
                                Console.WriteLine(jucator.Name + " , " + jucator.School);
                            break;
                        case 2:
                            Console.WriteLine("ID Echipa: ");
                            var idEchipa = int.Parse(Console.ReadLine() ?? string.Empty);
                            e = service.FindEchipa(idEchipa);
                            Console.WriteLine("ID Meci: ");
                            var idMeci = int.Parse(Console.ReadLine() ?? string.Empty);
                            m = service.FindMeci(idMeci);
                            Console.WriteLine($"Jucatorii activi ai echipei {e.Name} din meciul din {m.Date} sunt: ");
                            foreach (var jucator in service.JucatoriiActiviAiUneiEchipeDeLaMeciulX(e, m))
                            {
                                Console.WriteLine(jucator.Name + " , " + jucator.School);
                            }
                            break;
                        case 3:
                            Console.WriteLine("Din data de: ");
                            var d1 = DateTime.Parse(Console.ReadLine() ?? string.Empty);
                            Console.WriteLine("Pana in data de: ");
                            var d2 = DateTime.Parse(Console.ReadLine() ?? string.Empty);
                            foreach (var meci in service.MeciuriDinPerioadaX(d1, d2))
                            {
                                Console.WriteLine(meci.Team1.Name + " vs " + meci.Team2.Name + " din " + meci.Date);
                            }
                            break;
                        case 4:
                            Console.WriteLine("ID Meci: ");
                            var idM = int.Parse(Console.ReadLine() ?? string.Empty);
                            m = service.FindMeci(idM);
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