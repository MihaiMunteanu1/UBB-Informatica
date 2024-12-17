using System.Runtime.Serialization;

namespace Lab9.model;

public class MessageTask : Task
{
    private string _message;
    private string _from;
    private string _to;
    private DateTime _date;

    private static string _dateTimeFormatter = "yyyy-MM-dd HH:mm";

    private static string GetDateFormatter()
    {
        return _dateTimeFormatter;
    }

    public MessageTask(string id, string description, string message, string from, string to, DateTime date) : base(id,
        description)
    {
        _message = message;
        _from = from;
        _to = to;
        _date = date;
    }

    public override void Execute()
    {
        Console.WriteLine(_date.ToString(_dateTimeFormatter) + ": " + _message);
    }
}