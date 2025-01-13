package ubb.scs.map.sem13map.service;

import ubb.scs.map.sem13map.domain.*;
import ubb.scs.map.sem13map.repository.Repository;

import java.time.YearMonth;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class Service {
    private Repository<String, Angajat> repoAngajat;
    private Repository<Tuple<String>, Pontaj> repoPontaj;
    private Repository<String, Sarcina> repoSarcina;

    public Service(Repository<String, Angajat> repoAngajat, Repository<Tuple<String>, Pontaj> repoPontaj, Repository<String, Sarcina> repoSarcina) {
        this.repoAngajat = repoAngajat;
        this.repoPontaj = repoPontaj;
        this.repoSarcina = repoSarcina;
    }

    public List<Angajat> getEmployeesOrderedByLevelAndRatePerHour(){
        return StreamSupport.stream(repoAngajat.findAll().spliterator(), false)
                .sorted(Comparator.comparing(Angajat::getNivel)
                        .thenComparing(Comparator.comparing(Angajat::getVenitPeOra).reversed())).toList();
    }

    public Map<Dificultate, Double> getAverageTaskTime(){
        return StreamSupport.stream(repoSarcina.findAll().spliterator(), false)
                .collect(Collectors.groupingBy(Sarcina::getDificultate, Collectors.averagingDouble(Sarcina::getNrOreEstimate)));
    }

    public List<Pair<Angajat, Double>> getTopBestPaidEmployees(int limit, int year){
        return StreamSupport.stream(repoPontaj.findAll().spliterator(), false)
                .filter(p->p.getData().getYear()==year)
                .collect(Collectors.groupingBy(Pontaj::getAngajat, Collectors.summingDouble(
                        p ->
                            p.getSarcina().getNrOreEstimate()*p.getAngajat().getVenitPeOra()
                ))).entrySet().stream().map(e -> new Pair<>(e.getKey(), e.getValue()))
                .sorted(Comparator.comparing(Pair::getRight)).limit(limit)
                .collect(Collectors.toList());
    }

    public List<Pair<Angajat, Double>> getEmployeeSalaries(YearMonth yearMonth){
        return StreamSupport.stream(repoPontaj.findAll().spliterator(), false)
                .filter(p->p.getData().getYear() == yearMonth.getYear() && p.getData().getMonth()==yearMonth.getMonth())
                .collect(Collectors.groupingBy(Pontaj::getAngajat, Collectors.summingDouble(
                        p ->
                                p.getSarcina().getNrOreEstimate()*p.getAngajat().getVenitPeOra()
                ))).entrySet().stream().map(e -> new Pair<>(e.getKey(), e.getValue()))
                .sorted(Comparator.comparing((Pair<Angajat, Double> p)->p.getLeft().getNivel()).thenComparing(p->p.getRight()))
                .collect(Collectors.toList());
    }

}
