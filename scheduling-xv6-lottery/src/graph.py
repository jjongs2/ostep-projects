from re import compile
from sys import argv, exit

import matplotlib.pyplot as plt


def parse_output(file):
    iterations = [0]
    ticks = dict()
    tickets = dict()

    header_pattern = compile(r'^Iteration (\d+)')
    body_pattern = compile(r'^PID (\d+) \| Tickets (\d+) \| Ticks (\d+)')

    with open(file, 'r') as f:
        for line in f:
            if match := header_pattern.match(line):
                iterations.append(int(match.group(1)))
            elif match := body_pattern.match(line):
                pid, ticket_count, tick_count = map(int, match.groups())
                if pid not in ticks:
                    ticks[pid] = [0]
                    tickets[pid] = ticket_count
                ticks[pid].append(tick_count)

    return iterations, ticks, tickets


def plot_results(iterations, ticks, tickets, filename):
    plt.figure(figsize=(10, 5), facecolor='#eeeeee', layout='tight')

    for pid, tick_list in ticks.items():
        plt.plot(
            iterations, tick_list,
            marker='o',
            label=f'Process {pid} ({tickets[pid]} tickets)',
        )

    plt.xlabel('Iteration')
    plt.ylabel('Ticks')
    plt.title('Lottery Scheduler')
    plt.legend()
    plt.grid(True)

    plt.savefig(filename)
    plt.show()


def main():
    if len(argv) != 2:
        print('Usage: python graph.py <output_file>')
        exit(1)

    filename = 'graph.png'
    iterations, ticks, tickets = parse_output(argv[1])
    plot_results(iterations, ticks, tickets, filename)
    print(f'Graph saved as {filename}')


if __name__ == '__main__':
    main()
