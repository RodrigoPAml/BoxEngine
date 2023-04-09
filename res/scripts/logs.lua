function log(value)
	__log__(_utils_.to_string(value))
end

function warning(value)
	__warning__(_utils_.to_string(value))
end

function error(value)
	__error__(_utils_.to_string(value))
end