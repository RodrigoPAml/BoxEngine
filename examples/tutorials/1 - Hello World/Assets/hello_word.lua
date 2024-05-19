-- example of basic script lifecycle
function hello_word.start()
    engine.log('Hello World - Start')
end

function hello_word.update()
    engine.log('Hello World - Updating')
end

function hello_word.destroy()
    engine.log('Hello World - Destroy')
end
