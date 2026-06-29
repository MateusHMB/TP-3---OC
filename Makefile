# ============================================================
# Makefile — TP03 Hierarquia de Memoria
# Uso: make         → compila tudo
#      make run     → roda todos os algoritmos
#      make perf    → mede com perf (requer Linux + perf instalado)
#      make valgrind_hanoi → simula cache com valgrind (hanoi recursivo)
#      make clean   → remove binarios
# ============================================================

CC      = gcc
CFLAGS  = -O0 -g   # sem otimizacao para resultados de cache mais realistas

BINS    = bubblesort radixsort quicksort hanoi_recursivo hanoi_iterativo

PERF_EVENTS = cache-references,cache-misses,task-clock,cycles,instructions

all: $(BINS)

bubblesort: bubblesort.c
	$(CC) $(CFLAGS) -o bubblesort bubblesort.c

radixsort: radixsort.c
	$(CC) $(CFLAGS) -o radixsort radixsort.c

quicksort: quicksort.c
	$(CC) $(CFLAGS) -o quicksort quicksort.c

hanoi_recursivo: hanoi_recursivo.c
	$(CC) $(CFLAGS) -o hanoi_recursivo hanoi_recursivo.c

hanoi_iterativo: hanoi_iterativo.c
	$(CC) $(CFLAGS) -o hanoi_iterativo hanoi_iterativo.c

# ---------- execucao simples ----------
run: all
	./bubblesort
	./radixsort
	./quicksort
	./hanoi_recursivo
	./hanoi_iterativo

# ---------- perf (itens 3 e 4) ----------
# Para entrada pequena (N=1000 / N_DISCOS=20): compile com os defines padrao
# Para entrada grande (N=10000 / N_DISCOS=23): edite o #define no .c ou use:
#   gcc -O0 -g -DN=10000 -o bubblesort bubblesort.c

perf: all
	@echo "=== perf: bubblesort ==="
	perf stat -e $(PERF_EVENTS) ./bubblesort
	@echo ""
	@echo "=== perf: radixsort ==="
	perf stat -e $(PERF_EVENTS) ./radixsort
	@echo ""
	@echo "=== perf: quicksort ==="
	perf stat -e $(PERF_EVENTS) ./quicksort
	@echo ""
	@echo "=== perf: hanoi recursivo ==="
	perf stat -e $(PERF_EVENTS) ./hanoi_recursivo
	@echo ""
	@echo "=== perf: hanoi iterativo ==="
	perf stat -e $(PERF_EVENTS) ./hanoi_iterativo

# ---------- valgrind cachegrind (item 5) ----------
# Executa apenas hanoi recursivo com entrada pequena (conforme enunciado)
# Para alterar parametros de cache, use as flags abaixo como exemplo:
#   --I1=<size>,<assoc>,<line>
#   --D1=<size>,<assoc>,<line>
#   --LL=<size>,<assoc>,<line>

valgrind_hanoi: hanoi_recursivo
	@echo "=== valgrind padrao ==="
	valgrind --tool=cachegrind ./hanoi_recursivo
	@echo ""
	@echo "=== valgrind: cache L1 menor (8KB, 2-way, 64B) ==="
	valgrind --tool=cachegrind --I1=8192,2,64 --D1=8192,2,64 ./hanoi_recursivo
	@echo ""
	@echo "=== valgrind: cache L1 maior (64KB, 8-way, 64B) ==="
	valgrind --tool=cachegrind --I1=65536,8,64 --D1=65536,8,64 ./hanoi_recursivo

# ---------- item 6: comparacao recursivo vs iterativo com perf ----------
perf_hanoi_compare: hanoi_recursivo hanoi_iterativo
	@echo "=== ANTES (recursivo) ==="
	perf stat -e $(PERF_EVENTS) ./hanoi_recursivo
	@echo ""
	@echo "=== DEPOIS (iterativo cache-friendly) ==="
	perf stat -e $(PERF_EVENTS) ./hanoi_iterativo

clean:
	rm -f $(BINS) cachegrind.out.*

# ============================================================
# INSTRUCOES RAPIDAS
# ============================================================
# 1. Instalar perf (Ubuntu/Debian):
#      sudo apt install linux-tools-common linux-tools-$(uname -r)
#
# 2. Instalar valgrind:
#      sudo apt install valgrind
#
# 3. Para entrada grande nos algoritmos de ordenacao, recompile com:
#      gcc -O0 -g -DN=10000 -o bubblesort bubblesort.c
#      gcc -O0 -g -DN=10000 -o radixsort  radixsort.c
#      gcc -O0 -g -DN=10000 -o quicksort  quicksort.c
#
# 4. Para entrada grande no Hanoi, edite #define N_DISCOS 23 nos .c
#    (cuidado: 2^23 = ~8 milhoes de movimentos, pode demorar no valgrind)
# ============================================================
