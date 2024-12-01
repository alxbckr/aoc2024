new:
ifdef day
	@mkdir ./day$(day)
	@touch ./day$(day)/day$(day).cpp
	@touch ./day$(day)/input-test.txt
	@touch ./day$(day)/input.txt
else
	@echo 'Missing argument day=<n>'
endif

build:
ifdef day
	g++ ./day$(day)/day$(day).cpp -o ./day$(day)/day$(day).out
else
	@echo 'Missing argument day=<n>'
endif

run: build
ifdef day
ifdef part
	./day$(day)/day$(day).out ./day$(day)/input.txt $(part)
else
	./day$(day)/day$(day).out ./day$(day)/input.txt
endif
else
	@echo 'Missing argument day=<n>'
endif

test: build
ifdef day
ifdef part
	./day$(day)/day$(day).out ./day$(day)/input-test.txt $(part)
else
	./day$(day)/day$(day).out ./day$(day)/input-test.txt
endif
else
	@echo 'Missing argument day=<n>'
endif