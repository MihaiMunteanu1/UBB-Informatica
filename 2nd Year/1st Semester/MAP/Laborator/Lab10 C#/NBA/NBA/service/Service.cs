using NBA.domain;
using NBA.repository;

namespace NBA.service;

public class Service
{
    private IRepository<int, Echipa> echipe;
    private IRepository<int, Elev> elevi;
    private IRepository<int, Jucator> jucatori;
    private IRepository<int, Meci> meciuri;
    private IRepository<int, JucatorActiv> jucatoriActivi;

    public Service(IRepository<int, Echipa> echipe, IRepository<int, Elev> elevi, IRepository<int, Jucator> jucatori, IRepository<int, Meci> meciuri, IRepository<int, JucatorActiv> jucatoriActivi)
    {
        this.echipe = echipe;
        this.elevi = elevi;
        this.jucatori = jucatori;
        this.meciuri = meciuri;
        this.jucatoriActivi = jucatoriActivi;
    }

    public IEnumerable<Jucator> JucatoriiUneiEchipe(Echipa echipa)
    {
        return jucatori.FindAll().Where(j =>
        {
            Jucator jucator = (Jucator)j;
            return j.Team.Equals(echipa);
        });

    }
    
    public IEnumerable<Jucator> JucatoriiActiviAiUneiEchipeDeLaMeciulX(Echipa echipa, Meci meci)
    {
        return
            from jucatorActiv in jucatoriActivi.FindAll()
            join jucator in jucatori.FindAll()
                on jucatorActiv.idPlayer equals jucator.id
            where jucatorActiv.idGame == meci.id && jucator.Team.id == echipa.id
            select jucator;
    }
    
    public IEnumerable<Meci> MeciuriDinPerioadaX(DateTime beginingDate, DateTime endingDate)
    {
        return
            from meci in meciuri.FindAll()
            where meci.Date >= beginingDate && meci.Date <= endingDate
            select meci;
    }
    
    public string ScorulUnuiMeci2(Meci meci)
    {
        int scorEchipa1 =
            (from jucatorActiv in jucatoriActivi.FindAll()
                join jucator in jucatori.FindAll()
                    on jucatorActiv.idPlayer equals jucator.id
                join echipa in echipe.FindAll()
                    on jucator.Team.id equals echipa.id
                where jucatorActiv.idGame == meci.id
                      && meci.Team1.id == echipa.id
                select jucatorActiv.nrPoints).Sum();

        int scorEchipa2 =
            (from jucatorActiv in jucatoriActivi.FindAll()
                join jucator in jucatori.FindAll()
                    on jucatorActiv.idPlayer equals jucator.id
                join echipa in echipe.FindAll()
                    on jucator.Team.id equals echipa.id
                where jucatorActiv.idGame == meci.id
                      && meci.Team2.id == echipa.id
                select jucatorActiv.nrPoints).Sum();

        return scorEchipa1.ToString() + " - " + scorEchipa2.ToString();
    }
    
    public Echipa findEchipa(int id)
    {
        return echipe.FindOne(id);
    }

    public Meci findMeci(int id)
    {
        return meciuri.FindOne(id);
    }
}