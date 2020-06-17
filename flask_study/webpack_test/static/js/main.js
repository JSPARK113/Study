import tools from "./tools.js";
import $ from "jquery";
import '../css/main.css'

const Tools = tools();
const Event = {
  init: function () {
    $("#add-todo-item").on("click", function (e) {
      e.preventDefault();
      Tools.addTodoItem();
      $(".todo-item-done").on('click', Tools.completeTodoItem)
    });

    $("#todo-list").on("click", ".todo-item-delete", function (e) {
      var item = this;
      Tools.deleteTodoItem(e, item);
    });
  },
};

Event.init();
