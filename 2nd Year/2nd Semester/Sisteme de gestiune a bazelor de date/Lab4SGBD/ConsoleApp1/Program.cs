using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Configuration;
using System.Data.SqlClient;
using System.Threading;

namespace ConsoleApp1
{
    internal class Program
    {
        static string connectionString = ConfigurationManager.ConnectionStrings["con"]?.ConnectionString;

        static int maxRetries = 5;

        static void Main()
        {
            if (string.IsNullOrWhiteSpace(connectionString))
            {
                Console.WriteLine("Connection string-ul nu este configurat corect");
                return;
            }

            Thread t1 = new Thread(() => ExecuteWithRetry("DeadlockT1"));
            Thread t2 = new Thread(() => ExecuteWithRetry("DeadlockT2"));

            t1.Start();
            t2.Start();

            t1.Join();
            t2.Join();

            Console.WriteLine("Executia s-a încheiat.");
        }

        static void ExecuteWithRetry(string procedureName)
        {
            int attempt = 0;
            bool ok = false;

            while (attempt < maxRetries && !ok)
            {
                attempt++;
                try
                {
                    using (SqlConnection connection = new SqlConnection(connectionString))
                    {
                        connection.Open();
                        using (SqlCommand command = new SqlCommand(procedureName, connection))
                        {
                            command.CommandType = System.Data.CommandType.StoredProcedure;
                            command.ExecuteNonQuery();
                            Console.WriteLine($"[{procedureName}] Executed succesfully at attempt: #{attempt}");
                            ok = true;
                        }
                    }
                }
                catch (SqlException ex)
                {
                    if (ex.Number == 1205) // eroare deadlock
                    {
                        Console.WriteLine($"[{procedureName}] Deadlock at attempt: #{attempt}. Retrying...");
                        Thread.Sleep(1000); // wait delay
                    }
                    else
                    {
                        Console.WriteLine($"[{procedureName}] SQL Error: {ex.Message}");
                        break;
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"[{procedureName}] Unexpected error: {ex.Message}");
                    break;
                }
            }

            if (!ok)
            {
                Console.WriteLine($"[{procedureName}] Failed after {maxRetries} tries");
            }
        }
    }
}
