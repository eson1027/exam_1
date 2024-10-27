# Exercise #1 (Due Sep. 23 noon, 2024)

1.a.
    Die yield (Phoenix8)
    = 1 / (1 + 0.05 cm^(-2) * 2.00 cm^2)^14
    = 0.2633312543

1.b.
    It is fabricated in an older technology. As plants age, their process gets tuned, and the defect rate decreases.

1.c.
    Dies per wafer (Phoenix8)
    = pi * (450 mm / 2)^2 / (200 mm^2) - pi * 450mm / sqrt(2 * 200 mm^2)
    = 724.529806

    floor(724.529806) = 724

    Profit (Phoenix8)
    = 724 * 0.2633312543 * 30 USD
    = 5719.5548434 USD

1.d.
    Die yield (RedDragon)
    = 1 / (1 + 0.04 cm^(-2) * 1.20 cm^2)^14
    = 0.51873080912

    Dies per wafer (RedDragon)
    = pi * (450 mm / 2)^2 / (120 mm^2) - pi * 450mm / sqrt(2 * 120 mm^2)
    = 1234.10438

    floor(1234.10438) = 1234

    Number of wafers (RedDragon)
    = 50000 / 1234 / 0.51873080912
    = 78.1111086162

    ceil(78.1111086162) = 79

1.e.
    Let x be the number of wafers allocated for Phoenix8.
    (100 - x) is the number of wafers allocated for RedDragon.
    Let f(x) be the profit.
    f(x) = x * (724 * 0.2633312543) * 30 USD + (100 - x) * (1234 * 0.51873080912) * 15 USD
         = (960170.72768 - 3882.15 * x) USD
    Max Profit -> x=0, We don't make any Pheonix8, since the yield is too low to make a profit.

1.f.
    Each wafer we have (1490 * 0.57747508282) good Pheonix4 dies.
    So we can make (1490 * 0.57747508282 / 2) packaged Pheonix4x2 chips.
    From above, we know we can make (724 * 0.2633312543) good Pheonix8 chips.
    Cost of making packages Pheonix4 chips = (3000 + (1490 * 0.57747508282 / 2) * x) / (1490 * 0.57747508282 / 2), where x is the cost of an interposers
    Cost of making Pheonix8 chips = 3000 / (724 * 0.2633312543)
    We want (3000 + (1490 * 0.57747508282 / 2) * x) / (1490 * 0.57747508282 / 2) < 3000 / (724 * 0.2633312543)
    x < 8.7623 USD.

1.g.
    Yield for single-core Pheonix8 = 1/(1+(0.05 * 2 * 1/8))^14 =0.84
    The probability that N are defect free on a chip: #combinations * (0.84)^N * (1-0.84)^(8-N)
    # defect-free # combinations Probability
    8	1	0.247875891
    7	8	0.377715644
    6	28	0.251810429
    5	56	0.095927782
    4	70	0.022839948
    3	56	0.003480373
    2	28	0.000331464
    1	8	1.80389E-05
    0	1	4.29497E-07
    The yield for 8 cores = 0.248
    The yield for 6 cores = 0.378+0.252 = 0.630
    The yield for 4 cores = 0.096+0.023 = 0.119
    724 * (0.248 * 30 + 0.630 * 25 + 0.119 * 20) = $18512.68
    This is much higher than just selling 8-core versions.
    Note that 4-core version should not be counted, since the number is too low to sell.

2.a.
    running without sleep = 0.5W
    running with sleep = 0.5W * (2/8) + 0.1W * (6/8) = 0.2W
    power saving = 0.5W - 0.2W = 0.3W

2.b.
    running without DVFS = 0.5W
    P=f*c*vdd^2, f_new=1/2f, vdd_new=0.7vdd
    P_new=1/2*(0.7)^2=0.245P
    power saving = 0.5 - 0.245 * 0.5 = 0.3775W

2.c.
    Core_high (1GHz): t=1, P = 0.5W, E = 1s * 0.5W = 0.5J
    Core_high (500MHz): t=2, P = 0.5W * 0.405245, E = 2s * 0.5W * 0.245 = 0.245J
    Core_low (333MHz): t=3, P = 0.3W, E=3s * 0.3W = 0.9J

2.d.
    Sleep on-demand may be difficult to schedule, since it's difficult
    to predict the workload in the future time frame. Therefore, there
    will be some delays before the core can response to a new workload.
    DVFS cannot scale for advanced process nodes, since the Vdd is now
    almost fixed. The performance reduction from the frequency is too
    much to sacrifice.
    Low-power core cannot handle high-performance workload and it may
    consume more energy than burst computing from high-power cores.
    Usually, we need to combine all above to achieve satisfactory low
    power and energy design.

3.a.
    | time               | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  |
    | number of requests | 600| 700| 800| 900| 500| 400| 300| 600| 600| 600|
    | number of provided | 900| 900| 900| 900| 900| 900| 900| 900| 900| 900|
    | number of rejected |   0|   0|   0|   0|   0|   0|   0|   0|   0|   0|
    | number of accepted | 600| 700| 800| 900| 500| 400| 300| 600| 600| 600|
    Total full-speed machines = 900+900+900+900+900+900+900+900+900+900 = 9000
    Total sleep-mode machines = (1000+1000+1000+1000+1000+1000+1000+1000+1000+1000) - 9000 = 1000
    Total power = 9000 * 100(Watt) + 1000 * 10(Watt) = 910000(Watt)
    Total rejected = 0+0+0+0+0+0+0+0+0+0 = 0
    Total accepted = 600+700+800+900+500+400+300+600+600+600 = 6000
    Rejection rate = 0/6000 = 0%
    Profit = 6000 * 1000(USD) - 0 * 2000(USD) - 910000(Watt) * 6(USD/Watt) = 6000000(USD)-0(USD)-5460000(USD) = 540000(USD)

3.b.
    Provisioned machines=600. So 400 machines are at sleep.
    | time               | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  |
    | number of requests | 600| 700| 800| 900| 500| 400| 300| 600| 600| 600|
    | number of provided | 600| 600| 600| 600| 600| 600| 600| 600| 600| 600|
    | number of rejected |   0| 100| 200| 300|   0|   0|   0|   0|   0|   0|
    | number of accepted | 600| 600| 600| 600| 500| 400| 300| 600| 600| 600|
    Total full-speed machines = 600+600+600+600+600+600+600+600+600+600 = 6000
    Total sleep-mode machines = (1000+1000+1000+1000+1000+1000+1000+1000+1000+1000) - 6000 = 4000
    Total power = 6000 * 100(Watt) + 4000 * 10(Watt) = 640000(Watt)
    Total rejected = 0+100+200+300+0+0+0+0+0+0 = 600
    Total accepted = 600+600+600+600+500+400+300+600+600+600 = 5400
    Rejection rate = 600/6000 = 10%
    Profit = 5400 * 1000(USD) - 600 * 2000(USD) - 640000(Watt) * 6(USD/Watt) = 5400000(USD)-1200000(USD)-3840000(USD) = 360000(USD).

3.c.
    List of provisioned machines:
    | time               | 0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9  |
    | number of requests | 600| 700| 800| 900| 500| 400| 300| 600| 600| 600|
    | number of provided | 600| 660| 770| 880| 990| 891| 802| 722| 660| 660|
    | number of rejected |   0|  40|  30|  20|   0|   0|   0|   0|   0|   0|
    | number of accepted | 600| 660| 770| 880| 500| 400| 300| 600| 600| 600|
    Total full-speed machines = 600+660+770+880+990+891+802+722+660+660 = 7635
    Total sleep-mode machines = (1000+1000+1000+1000+1000+1000+1000+1000+1000+1000) - 7635 = 2365
    Total power = 7635 * 100(Watt) + 2365 * 10(Watt) = 787150(Watt)
    Total rejected = 0+40+30+20+0+0+0+0+0+0 = 90
    Total accepted = 600+660+770+880+500+400+300+600+600+600 = 5910
    Rejection rate = 90/6000 = 1.5%
    Profit earned = 5910 * 1000(USD) - 90 * 2000(USD) - 787150(Watt) * 6(USD/Watt) = 5910000(USD)-180000(USD)-4722900(USD) = 1007100(USD)

3.d.
    Based on above answers. The provision method of problem c. earns most (1007100(USD)) with modest power consumption.
    And the second is the max provision method (problem a.), even though it consumes most power.
    The method still earns more without paying penalty of rejection.

4.a.
    1/(0.3+0.7/N) = 2.5

4.b.
    1/(0.3+0.7/8+0.04*8) = 1.413

4.c.
    1/(0.3+0.7/8+0.04*log(8)) = 1.97

4.d.
    1/(0.3+0.7/N+0.04log_2(N))

4.e.
    Speedup = 100/(100-P+P/N+4log_2(N))
    Solve for integer N.
    When trying possible N , we found that N=1 has the highest speedup for P=5%.
    N=1 Speedup=1
    N=2 Speedup=0.985222
    ...
    

