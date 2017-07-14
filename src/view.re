open ReasonJs.Dom;

open Notes_utils;

/* wut */
external setValue : Element.t => string => unit = "value" [@@bs.set];

let getFormElement () =>
  switch (document |> Document.querySelector "form") {
  | None => raise (Invalid_argument "getFormElement failed")
  | Some el => el
  };

let getTextarea () =>
  switch (getFormElement () |> Element.querySelector "textarea") {
  | None => raise (Invalid_argument "getTextarea failed")
  | Some el => el
  };

let getList () =>
  switch (document |> Document.querySelector "ul") {
  | None => raise (Invalid_argument "getList failed")
  | Some el => el
  };

let selectNote (note: complete_note) => {
  let form = getFormElement ();
  Element.setAttribute "data-note-id" note.id form;
  setValue (getTextarea ()) note.text;
  ()
};

let updateList () :unit => {
  let list = getList ();
  Element.setInnerHTML list "";
  Model.getNotes () |>
  List.iter (
    fun note => {
      let li = document |> Document.createElement "li";
      Element.setTextContent li note.text;
      Element.addEventListener
        "click"
        (
          fun _e => {
            selectNote (Model.getNoteById note.id);
            ()
          }
        )
        li;
      li |> Element.setAttribute "data-note-id" note.id;
      list |> Element.appendChild li;
      ()
    }
  );
  Model.saveNotes ();
  ()
};

let createList () => {
  let container = document |> Document.createElement "div";
  Element.setId container "notes-list-container";
  let ul = document |> Document.createElement "ul";
  Element.setId ul "notes-list";
  let button = document |> Document.createElement "button";
  Element.setId button "add-note-button";
  Element.setInnerText button "Dodaj";
  container |> Element.appendChild ul;
  container |> Element.appendChild button;
  button |>
  Element.addEventListener
    "click"
    (
      fun _e => {
        let _ = Model.addNote {text: ""};
        updateList ();
        ()
      }
    );
  container
};

let onInput _event => {
  let textarea = getTextarea ();
  let form = getFormElement ();
  let text =
    HtmlElement.value (
      switch (Element.asHtmlElement textarea) {
      | None => raise (Invalid_argument "lol")
      | Some el => el
      }
    );
  switch (form |> Element.getAttribute "data-note-id") {
  | None => raise (Invalid_argument "data-note-id missing")
  | Some id =>
    let _ = Model.updateNote {text, id};
    Model.saveNotes ()
  };
  updateList ();
  ()
};

let createForm () => {
  let form = document |> Document.createElement "form";
  Element.setId form "note-form";
  let textarea = document |> Document.createElement "textarea";
  form |> Element.appendChild textarea;
  textarea |> Element.addEventListener "input" onInput;
  form
};

let init (mainSelector: string) :unit => {
  Model.loadNotes ();
  let mainEl =
    switch (document |> Document.querySelector mainSelector) {
    | None => raise (Invalid_argument ("document.querySelector " ^ mainSelector))
    | Some el => el
    };
  let listEl = createList ();
  let formEl = createForm ();
  mainEl |> Element.appendChild listEl;
  mainEl |> Element.appendChild formEl;
  let note = List.nth (Model.getNotes ()) 0;
  selectNote note;
  updateList ();
  ()
};
