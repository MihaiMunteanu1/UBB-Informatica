﻿using NBA.domain;
using NBA.repository;

namespace NBA.service;

public class Service(
    IRepository<int, Echipa> echipe,
    IRepository<int, Elev> elevi,
    IRepository<int, Jucator> jucatori,
    IRepository<int, Meci> meciuri,
    IRepository<int, JucatorActiv> jucatoriActivi)
{
    private IRepository<int, Elev> _elevi = elevi;

    public IEnumerable<Jucator> JucatoriiUneiEchipe(Echipa echipa)
    {
        return jucatori.FindAll().Where(j => j.Team.Equals(echipa));
    }
    
    public IEnumerable<Jucator> JucatoriiActiviAiUneiEchipeDeLaMeciulX(Echipa echipa, Meci meci)
    {
        return
            from jucatorActiv in jucatoriActivi.FindAll()
            join jucator in jucatori.FindAll()
                on jucatorActiv.IdPlayer equals jucator.Id
            where jucatorActiv.IdGame == meci.Id && jucator.Team.Id == echipa.Id
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
        var scorEchipa1 =
            (from jucatorActiv in jucatoriActivi.FindAll()
                join jucator in jucatori.FindAll()
                    on jucatorActiv.IdPlayer equals jucator.Id
                join echipa in echipe.FindAll()
                    on jucator.Team.Id equals echipa.Id
                where jucatorActiv.IdGame == meci.Id
                      && meci.Team1.Id == echipa.Id
                select jucatorActiv.NrPoints).Sum();

        var scorEchipa2 =
            (from jucatorActiv in jucatoriActivi.FindAll()
                join jucator in jucatori.FindAll()
                    on jucatorActiv.IdPlayer equals jucator.Id
                join echipa in echipe.FindAll()
                    on jucator.Team.Id equals echipa.Id
                where jucatorActiv.IdGame == meci.Id
                      && meci.Team2.Id == echipa.Id
                select jucatorActiv.NrPoints).Sum();

        return scorEchipa1 + " - " + scorEchipa2;
    }
    
    public Echipa FindEchipa(int id)
    {
        return echipe.FindOne(id) ?? throw new InvalidOperationException();
    }

    public Meci FindMeci(int id)
    {
        return meciuri.FindOne(id) ?? throw new InvalidOperationException();
    }
}